import 'package:flutter/material.dart';
import 'package:project_rotary/app/auth/presentation/pages/singin_page.dart';
import 'package:project_rotary/app/auth/presentation/pages/signup_page.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      theme: ThemeData(primarySwatch: Colors.purple),
      initialRoute: '/',
      routes: {
        '/': (context) => SingInPage(),
        '/signup': (context) => SignUpPage(),
      },
    );
  }
}
