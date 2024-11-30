// ignore_for_file: library_private_types_in_public_api, camel_case_types, unused_local_variable, unused_field, file_names

import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:animated_button/animated_button.dart';

class RequestPage extends StatefulWidget {
  const RequestPage({super.key});

  @override
  _RequestPageState createState() => _RequestPageState();
}

class _RequestPageState extends State<RequestPage> {
  late Query dbRef;
  DatabaseReference reference = FirebaseDatabase.instance
      .reference()
      .child('FLUTTER')
      .child('lj496azHzjSQi0hP3GJ65MfFMbA2');

  @override
  void initState() {
    super.initState();
    dbRef = reference;
  }

  @override
  Widget build(BuildContext context) {
    double w = MediaQuery.of(context).size.width;
    return Scaffold(
      backgroundColor: Colors.white,
      body: Center(
          child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          AnimatedButton(
            color: const Color.fromARGB(255, 2, 7, 161),
            onPressed: () {
              reference.child('request').set('yes');
            },
            enabled: true,
            shadowDegree: ShadowDegree.light,
            child: const Text(
              'Request Nurse',
              style: TextStyle(
                fontSize: 22,
                color: Colors.white,
                fontWeight: FontWeight.w500,
              ),
            ),
          ),
          const SizedBox(
            height: 40,
          ),
          AnimatedButton(
            color: Color.fromARGB(255, 161, 2, 2),
            onPressed: () {
              reference.child('ambulance').set('yes');
            },
            enabled: true,
            width: 230,
            shadowDegree: ShadowDegree.light,
            child: const Text(
              'Request Ambulance',
              style: TextStyle(
                fontSize: 22,
                color: Colors.white,
                fontWeight: FontWeight.w500,
              ),
            ),
          )
        ],
      )),
    );
  }
}
