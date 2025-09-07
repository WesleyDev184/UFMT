package com.bananachat.backend.controller;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jms.annotation.JmsListener;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.messaging.simp.SimpMessageHeaderAccessor;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.stereotype.Controller;

import com.bananachat.backend.jms.MessageProducer;
import com.bananachat.backend.model.ChatMessage;

@Controller
public class ChatController {

    private static final Logger LOGGER = LoggerFactory.getLogger(ChatController.class);

    @Autowired
    private MessageProducer messageProducer;

    @Autowired
    private SimpMessagingTemplate messagingTemplate; // Usado para enviar mensagens via WebSocket

    /**
     * Manipula o envio de mensagens de chat.
     * Recebe mensagens do cliente via WebSocket no destino "/app/chat.sendMessage".
     *
     * @param chatMessage A mensagem recebida do cliente.
     */
    @MessageMapping("/chat.sendMessage")
    public void sendMessage(@Payload ChatMessage chatMessage) {
        // Envia a mensagem para o broker JMS para processamento assíncrono.
        messageProducer.sendMessage(chatMessage);
    }

    /**
     * Manipula a adição de um novo usuário ao chat.
     * Recebe mensagens do cliente via WebSocket no destino "/app/chat.addUser".
     *
     * @param chatMessage A mensagem contendo informações do usuário que entrou.
     * @param headerAccessor Permite acessar informações da sessão WebSocket.
     */
    @MessageMapping("/chat.addUser")
    public void addUser(@Payload ChatMessage chatMessage, SimpMessageHeaderAccessor headerAccessor) {
        // Adiciona o nome de usuário na sessão do WebSocket
        headerAccessor.getSessionAttributes().put("username", chatMessage.getSender());
        // Envia a mensagem de "JOIN" para o broker JMS
        messageProducer.sendMessage(chatMessage);
    }

    /**
     * Escuta o tópico JMS para receber novas mensagens.
     * Assim que uma mensagem chega no tópico JMS, este método é invocado.
     *
     * @param chatMessage A mensagem que foi consumida do tópico JMS.
     */
    @JmsListener(destination = "${jms.chat.topic}")
    public void receiveMessageFromJms(ChatMessage chatMessage) {
        LOGGER.info("Mensagem recebida do JMS, transmitindo para o WebSocket no tópico /topic/public");
        
        // Envia a mensagem recebida para todos os clientes inscritos no tópico WebSocket "/topic/public".
        // O frontend React estará escutando neste destino.
        messagingTemplate.convertAndSend("/topic/public", chatMessage);
    }
}
