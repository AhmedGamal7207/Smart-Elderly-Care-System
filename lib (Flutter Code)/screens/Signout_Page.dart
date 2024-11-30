// ignore_for_file: library_private_types_in_public_api, camel_case_types, unused_local_variable, unused_field, file_names

import 'package:elderly_care_v1/backend/auth.dart';
import 'package:flutter/material.dart';
import 'package:animated_button/animated_button.dart';

class SignOutPage extends StatefulWidget {
  const SignOutPage({super.key});

  @override
  _SignOutPageState createState() => _SignOutPageState();
}

class _SignOutPageState extends State<SignOutPage> {
  @override
  Widget build(BuildContext context) {
    double w = MediaQuery.of(context).size.width;
    return Scaffold(
      backgroundColor: Colors.white,
      body: Center(
        child: AnimatedButton(
          color: Color.fromARGB(255, 130, 0, 216),
          onPressed: () {
            Auth().signOut();
          },
          enabled: true,
          shadowDegree: ShadowDegree.light,
          child:
              const Row(mainAxisAlignment: MainAxisAlignment.center, children: [
            Text(
              'Sign Out',
              style: TextStyle(
                fontSize: 22,
                color: Color.fromARGB(255, 255, 255, 255),
                fontWeight: FontWeight.w500,
              ),
            ),
            SizedBox(width: 10),
            Icon(Icons.logout_sharp, color: Colors.white),
          ]),
        ),
      ),
    );
  }
}
