import 'package:flutter/material.dart';
import 'package:project_rotary/core/components/button.dart';
import 'package:project_rotary/core/components/input_field.dart';
import 'package:project_rotary/core/components/password_field.dart';
import 'package:project_rotary/features/auth/presentation/controller/auth_controller.dart';
import 'package:project_rotary/features/auth/data/fake_auth_repository.dart';
import 'package:project_rotary/features/auth/domain/dto/signup_dto.dart';

class SignUpForm extends StatefulWidget {
  const SignUpForm({super.key});

  @override
  State<SignUpForm> createState() => _SignUpFormState();
}

class _SignUpFormState extends State<SignUpForm> {
  final authController = AuthController(FakeAuthRepository());

  late TextEditingController nameController;
  late TextEditingController phoneController;
  late TextEditingController emailController;
  late TextEditingController passwordController;
  late TextEditingController confirmPasswordController;

  @override
  void initState() {
    super.initState();
    nameController = TextEditingController();
    phoneController = TextEditingController();
    emailController = TextEditingController();
    passwordController = TextEditingController();
    confirmPasswordController = TextEditingController();
  }

  @override
  void dispose() {
    nameController.dispose();
    phoneController.dispose();
    emailController.dispose();
    passwordController.dispose();
    confirmPasswordController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    final primaryColor = Theme.of(context).primaryColor;

    return Card(
      shape: const RoundedRectangleBorder(
        borderRadius: BorderRadius.only(
          topLeft: Radius.circular(30),
          topRight: Radius.circular(30),
        ),
      ),
      child: Padding(
        padding: const EdgeInsets.symmetric(horizontal: 32.0, vertical: 16.0),
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            Text(
              "Criar conta",
              style: TextStyle(
                color: primaryColor,
                fontSize: 25,
                fontWeight: FontWeight.w500,
              ),
            ),
            const SizedBox(height: 16),
            InputField(
              controller: nameController,
              hint: "Nome",
              icon: Icons.person,
            ),
            const SizedBox(height: 8),
            InputField(
              controller: emailController,
              hint: "Email",
              icon: Icons.email,
            ),
            const SizedBox(height: 8),
            InputField(
              controller: phoneController,
              hint: "Telefone",
              icon: Icons.phone,
            ),
            const SizedBox(height: 8),
            PasswordField(controller: passwordController, hint: "Senha"),
            const SizedBox(height: 8),
            PasswordField(
              controller: confirmPasswordController,
              hint: "Confirmar senha",
            ),
            const SizedBox(height: 16),
            Button(
              onPressed: () async {
                bool success = await authController.signup(
                  signUpDTO: SignUpDTO(
                    email: emailController.text,
                    password: passwordController.text,
                    confirmPassword: confirmPasswordController.text,
                    name: nameController.text,
                    phone: phoneController.text,
                  ),
                );

                if (context.mounted) {
                  if (success) {
                    Navigator.pushReplacementNamed(context, '/signup');
                  } else {
                    ScaffoldMessenger.of(context).showSnackBar(
                      SnackBar(
                        content: Text(
                          authController.error ?? 'Erro ao fazer login',
                        ),
                      ),
                    );
                  }
                }
              },
              text: "Criar conta",
              backgroundColor: Colors.green,
              isFullWidth: true,
            ),
            const SizedBox(height: 8),
            TextButton(
              onPressed: () => Navigator.pop(context),
              child: const Text("Já tem uma conta? Faça login"),
            ),
          ],
        ),
      ),
    );
  }
}
