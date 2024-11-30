// ignore_for_file: library_private_types_in_public_api, camel_case_types, unused_local_variable, unused_field, file_names

import 'package:animated_button/animated_button.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:firebase_database/ui/firebase_animated_list.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class PredictPage extends StatefulWidget {
  const PredictPage({super.key});

  @override
  _PredictPageState createState() => _PredictPageState();
}

class _PredictPageState extends State<PredictPage> {
  late Query dbRef;
  DatabaseReference reference =
      FirebaseDatabase.instance.reference().child('PYTHON');
  //.child('lj496azHzjSQi0hP3GJ65MfFMbA2');

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
        appBar: AppBar(
          backgroundColor: Colors.white,
          elevation: 0,
          centerTitle: true,
          shadowColor: Colors.black.withOpacity(.5),
          title: Text(
            'PRESS PREDICT',
            style: TextStyle(
                color: Colors.black.withOpacity(.7),
                fontWeight: FontWeight.w600,
                letterSpacing: 1),
          ),
        ),
        body: FirebaseAnimatedList(
            query: dbRef,
            itemBuilder: (BuildContext context, DataSnapshot snapshot,
                Animation<double> animation, int index) {
              Map data = snapshot.value as Map;
              return Center(
                child: Padding(
                    padding: EdgeInsets.symmetric(vertical: w / 6),
                    child: Column(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        const Icon(
                          Icons.waves,
                          size: 100,
                          color: Colors.blue,
                        ),
                        const Text(
                          'Wind Speed',
                          style: TextStyle(
                            fontSize: 24,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                        Text(
                          '${data['windValue']} m/s',
                          style: const TextStyle(
                            fontSize: 36,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                        const SizedBox(height: 20),
                        const Icon(
                          Icons.arrow_upward,
                          size: 100,
                          color: Colors.red,
                        ),
                        const Text(
                          'Max Wind Speed',
                          style: TextStyle(
                            fontSize: 24,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                        Text(
                          '${data['maxValue']} m/s',
                          style: const TextStyle(
                            fontSize: 36,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                        const SizedBox(height: 40),
                        AnimatedButton(
                          height: 50,
                          width: 120,
                          color: const Color(0xFF2596BE),
                          onPressed: () {
                            reference
                                .child('lj496azHzjSQi0hP3GJ65MfFMbA2')
                                .child('predict')
                                .set('yes');
                          },
                          enabled: true,
                          shadowDegree: ShadowDegree.light,
                          child: const Text(
                            'Predict',
                            style: TextStyle(
                              fontSize: 18,
                              color: Colors.white,
                              fontWeight: FontWeight.w500,
                            ),
                          ),
                        ),
                      ],
                    )),
              );
            }));
  }
}
