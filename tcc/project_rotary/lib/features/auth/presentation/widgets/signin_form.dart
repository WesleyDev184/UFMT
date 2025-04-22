import 'package:flutter/material.dart';
import 'package:project_rotary/core/components/button.dart';
import 'package:project_rotary/core/components/input_field.dart';
import 'package:project_rotary/core/components/password_field.dart';
import 'package:project_rotary/features/auth/presentation/controller/auth_controller.dart';
import 'package:project_rotary/features/auth/data/fake_auth_repository.dart';
import 'package:project_rotary/features/auth/domain/dto/signin_dto.dart';

class SingInForm extends StatefulWidget {
  const SingInForm({super.key});

  @override
  _SingInFormState createState() => _SingInFormState();
}

class _SingInFormState extends State<SingInForm> {
  late final AuthController authController;
  late final TextEditingController emailController;
  late final TextEditingController passwordController;

  @override
  void initState() {
    super.initState();
    authController = AuthController(FakeAuthRepository());
    emailController = TextEditingController();
    passwordController = TextEditingController();
  }

  @override
  void dispose() {
    emailController.dispose();
    passwordController.dispose();
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
        padding: const EdgeInsets.all(32.0),
        child: Column(
          mainAxisSize: MainAxisSize.min,
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Text(
              "Login",
              style: TextStyle(
                color: primaryColor,
                fontSize: 32,
                fontWeight: FontWeight.w500,
              ),
            ),
            const SizedBox(height: 10),
            const Text(
              "Entre com sua conta",
              style: TextStyle(color: Colors.grey),
            ),
            const SizedBox(height: 20),
            InputField(
              controller: emailController,
              hint: "Email",
              icon: Icons.email,
            ),
            const SizedBox(height: 10),
            PasswordField(controller: passwordController, hint: "Senha"),
            const SizedBox(height: 10),
            Align(
              alignment: Alignment.centerRight,
              child: TextButton(
                onPressed: () {},
                child: const Text(
                  "Esqueci minha senha",
                  style: TextStyle(color: Colors.grey),
                ),
              ),
            ),
            const SizedBox(height: 10),
            Button(
              onPressed: () async {
                bool success = await authController.signin(
                  signInDTO: SignInDTO(
                    email: emailController.text,
                    password: passwordController.text,
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
              text: "Entrar",
              icon: Icon(Icons.login, color: Colors.white),
              backgroundColor: Colors.green,
              isFullWidth: true,
            ),
            const SizedBox(height: 10),
            Align(
              alignment: Alignment.center,
              child: TextButton(
                onPressed: () => Navigator.pushNamed(context, '/signup'),
                child: const Text(
                  "Não tenho uma conta? Registre-se",
                  style: TextStyle(color: Colors.deepPurple),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
