// ignore_for_file: file_names

import 'package:elderly_care_v1/screens/Home_Options.dart';
import 'package:elderly_care_v1/screens/Predict_Page.dart';
import 'package:elderly_care_v1/screens/Request_Page.dart';
import 'package:elderly_care_v1/screens/Signout_Page.dart';
import 'package:flutter/material.dart';

class HomePage extends StatefulWidget {
  const HomePage({super.key});

  @override
  HomePageState createState() => HomePageState();
}

class HomePageState extends State<HomePage> {
  var currentIndex = 0;
  final PageController _pageController =
      PageController(); // Controller for PageView

  @override
  void dispose() {
    _pageController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    Size size = MediaQuery.of(context).size;
    return Scaffold(
        //backgroundColor: Color.fromARGB(224, 205, 184, 115),
        extendBodyBehindAppBar: true,
        bottomNavigationBar: Container(
          color: Colors.transparent,
          height: size.width * .155,
          child: ListView.builder(
            itemCount: 4,
            scrollDirection: Axis.horizontal,
            padding: EdgeInsets.symmetric(horizontal: size.width * .024),
            itemBuilder: (context, index) => InkWell(
              onTap: () {
                setState(() {
                  currentIndex = index;
                  _pageController.animateToPage(
                    index,
                    duration: const Duration(milliseconds: 500),
                    curve: Curves.easeInOut,
                  );
                  // print(index);
                });
              },
              splashColor: Colors.transparent,
              highlightColor: Colors.transparent,
              child: Column(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  SizedBox(height: size.width * .014),
                  Icon(
                    listOfIcons[index],
                    size: size.width * .076,
                    color: currentIndex == index
                        ? const Color.fromARGB(
                            255, 130, 0, 216) // Highlighted color
                        : Colors.grey, // Inactive color,
                  ),
                  AnimatedContainer(
                    duration: const Duration(milliseconds: 1500),
                    curve: Curves.fastLinearToSlowEaseIn,
                    margin: EdgeInsets.only(
                      top: index == currentIndex ? 0 : size.width * .029,
                      right: size.width * .0422,
                      left: size.width * .0422,
                    ),
                    width: size.width * .153,
                    height: index == currentIndex ? size.width * .014 : 0,
                    decoration: BoxDecoration(
                      color: //Color.fromARGB(255, 2, 7, 161)
                          currentIndex == index
                              ? const Color.fromARGB(
                                  255, 130, 0, 216) // Highlighted shadow color
                              : Colors.transparent,
                      borderRadius: const BorderRadius.vertical(
                        top: Radius.circular(20),
                      ),
                      boxShadow: const [
                        BoxShadow(
                          color: Colors.red, // Shadow color and opacity
                          blurRadius: 5, // Spread of the shadow
                          offset: Offset(0, 3), // Offset of the shadow
                        )
                      ],
                    ),
                  ),
                ],
              ),
            ),
          ),
        ),
        body: PageView(
            controller: _pageController,
            onPageChanged: (index) {
              setState(() {
                currentIndex = index;
              });
            },
            children: [
              // Define your screens here for each index
              Container(
                decoration: const BoxDecoration(
                  gradient: LinearGradient(
                    begin: Alignment.topLeft,
                    end: Alignment.bottomRight,
                    colors: [
                      Color.fromARGB(255, 53, 141, 235),
                      Color.fromARGB(255, 2, 7, 161),
                    ],
                  ),
                ),
                child: const HomeOptions(),
              ),
              Container(
                decoration: const BoxDecoration(
                  gradient: LinearGradient(
                    begin: Alignment.topLeft,
                    end: Alignment.bottomRight,
                    colors: [
                      Color.fromARGB(255, 53, 141, 235),
                      Color.fromARGB(255, 2, 7, 161),
                    ],
                  ),
                ),
                child: const RequestPage(),
              ),
              Container(
                decoration: const BoxDecoration(
                  gradient: LinearGradient(
                    begin: Alignment.topLeft,
                    end: Alignment.bottomRight,
                    colors: [
                      Color.fromARGB(255, 53, 141, 235),
                      Color.fromARGB(255, 2, 7, 161),
                    ],
                  ),
                ),
                child: const PredictPage(),
              ),
              Container(
                  decoration: const BoxDecoration(
                    gradient: LinearGradient(
                      begin: Alignment.topLeft,
                      end: Alignment.bottomRight,
                      colors: [
                        Color.fromARGB(255, 53, 141, 235),
                        Color.fromARGB(255, 2, 7, 161),
                      ],
                    ),
                  ),
                  child: const SignOutPage())
            ])
        /*Container(
        decoration: const BoxDecoration(
          gradient: LinearGradient(
            begin: Alignment.topLeft, // Gradient Start
            end: Alignment.bottomRight, // Gradient End
            colors: [
              // BG Color
              Color.fromARGB(255, 53, 141, 235),
              Color.fromARGB(255, 2, 7, 161),
            ],
          ),
        ),
        child: Center(
          child: Text("Hello"),
        ),
      ),*/
        );
  }

  List<IconData> listOfIcons = [
    Icons.home_rounded,
    Icons.elderly,
    Icons.wind_power,
    Icons.logout,
  ];
}
