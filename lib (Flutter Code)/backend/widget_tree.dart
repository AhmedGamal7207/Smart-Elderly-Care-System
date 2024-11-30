// import 'package:elderly_care_v1/screens/home.dart';
import 'package:elderly_care_v1/screens/Home_Page.dart';
import 'package:flutter/material.dart';
import 'auth.dart';
import '../screens/Login_Page.dart';

class WidgetTree extends StatefulWidget {
  const WidgetTree({Key? key}) : super(key: key);

  @override
  State<WidgetTree> createState() => _WidgeTreeState();
}

class _WidgeTreeState extends State<WidgetTree> {
  @override
  Widget build(BuildContext context) {
    return StreamBuilder(
      stream: Auth().authStateChanges,
      builder: (context, snapshot) {
        if (snapshot.hasData) {
          return const HomePage();
        } else {
          return const LoginPage();
        }
      },
    );
  }
}
