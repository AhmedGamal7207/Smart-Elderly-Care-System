import 'package:elderly_care_v1/backend/auth.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class LoginPage extends StatefulWidget {
  const LoginPage({Key? key}) : super(key: key);

  @override
  _LoginPageState createState() => _LoginPageState();
}

class _LoginPageState extends State<LoginPage>
    with SingleTickerProviderStateMixin {
  // Class to do animation for only one time
  late AnimationController _controller;
  late Animation<double> _opacity;
  late Animation<double> _transform;
  final TextEditingController _controllerEmail = TextEditingController();
  final TextEditingController _controllerPassword = TextEditingController();

  Future<void> signInWithEmailAndPassword() async {
    try {
      await Auth().signInWithEmailAndPassword(
          email: _controllerEmail.text, password: _controllerPassword.text);
    } on FirebaseAuthException catch (e) {
      _showErrorMessage('Error during sign in: $e');
    }
  }

  void _showErrorMessage(String message) {
    ScaffoldMessenger.of(context)
        .showSnackBar(SnackBar(content: Text(message)));
  }

  @override
  void initState() {
    _controller = AnimationController(
      // Controls our first animation
      vsync: this,
      duration: const Duration(seconds: 3),
    );

    _opacity = Tween<double>(begin: 0, end: 1).animate(
      CurvedAnimation(
        parent: _controller,
        curve: Curves.ease,
      ),
    )..addListener(() {
        setState(() {});
      });

    _transform = Tween<double>(begin: 2, end: 1).animate(
      CurvedAnimation(
        parent: _controller,
        curve: Curves.fastLinearToSlowEaseIn,
      ),
    );

    _controller.forward();
    super.initState();
  }

  @override
  void dispose() {
    _controller.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    Size size = MediaQuery.of(context).size; // Size of my screen
    return Scaffold(
      extendBodyBehindAppBar: true, // Remove appbar location
      appBar: AppBar(
        backgroundColor: Colors.transparent, // Remove appbar color
        elevation: 0, // No elevation (like shadow)
        systemOverlayStyle: SystemUiOverlayStyle.light,
      ),
      body: ScrollConfiguration(
        behavior: MyBehavior(),
        child: SingleChildScrollView(
          // Box that have one widget to be scrolled
          child: SizedBox(
            height: size.height,
            child: Container(
              // Large container for all the screen
              alignment: Alignment.center,
              decoration: const BoxDecoration(
                gradient: LinearGradient(
                  begin: Alignment.topLeft, // Gradient Start
                  end: Alignment.bottomRight, // Gradient End
                  colors: [
                    // BG Color
                    Color.fromARGB(255, 152, 89, 255),
                    Color(0xffFF4184),
                  ],
                ),
              ),
              child: Opacity(
                // To control the fadeness
                opacity: _opacity.value,
                child: Transform.scale(
                  // To do the scaling transition at the beginning
                  scale: _transform.value,
                  child: Container(
                    // Our white box that contains the text fields
                    width: size.width * .9, //0.9
                    height: size.width * 0.8, //1.1
                    decoration: BoxDecoration(
                      // Decoration for that box
                      color: const Color.fromARGB(255, 255, 255, 255),
                      borderRadius: BorderRadius.circular(25),
                      boxShadow: [
                        BoxShadow(
                          color: Colors.black.withOpacity(.1),
                          blurRadius: 90,
                        ),
                      ],
                    ),
                    child: Column(
                      mainAxisAlignment: MainAxisAlignment
                          .spaceEvenly, // Like centralized spaces to the component
                      children: [
                        Text(
                          'Sign In',
                          style: TextStyle(
                            fontSize: 26,
                            fontWeight: FontWeight.w800,
                            color: Colors.black.withOpacity(.8),
                          ),
                        ),
                        MyTextField(Icons.email_outlined, 'Email...', false,
                            true, _controllerEmail),
                        MyTextField(Icons.lock_outline, 'Password...', true,
                            false, _controllerPassword),
                        Row(
                          mainAxisAlignment: MainAxisAlignment.center,
                          children: [
                            MyLoginButton(
                              'LOGIN',
                              2,
                              () {
                                signInWithEmailAndPassword();
                              },
                            ),
                          ],
                        ),
                      ],
                    ),
                  ),
                ),
              ),
            ),
          ),
        ),
      ),
    );
  }

  Widget MyTextField(IconData icon, String hintText, bool isPassword,
      bool isEmail, TextEditingController controller) {
    Size size = MediaQuery.of(context).size;
    return Container(
      height: size.width / 8,
      width: size.width / 1.3, //1.22
      alignment: Alignment.center,
      padding: EdgeInsets.only(right: size.width / 30),
      decoration: BoxDecoration(
        color: Colors.black.withOpacity(.05),
        borderRadius: BorderRadius.circular(10),
      ),
      child: TextField(
        controller: controller,
        style: TextStyle(color: Colors.black.withOpacity(.8)),
        obscureText: isPassword,
        keyboardType: isEmail ? TextInputType.emailAddress : TextInputType.text,
        decoration: InputDecoration(
          prefixIcon: Icon(
            icon,
            color: Colors.black.withOpacity(.7),
          ),
          border: InputBorder.none,
          hintMaxLines: 1,
          hintText: hintText,
          hintStyle:
              TextStyle(fontSize: 14, color: Colors.black.withOpacity(.5)),
        ),
      ),
    );
  }

  Widget MyLoginButton(String string, double width, VoidCallback voidCallback) {
    Size size = MediaQuery.of(context).size;
    return MaterialButton(
      highlightColor: Colors.transparent,
      splashColor: Colors.transparent,
      onPressed: voidCallback,
      child: Container(
        height: size.width / 8,
        width: size.width / width,
        alignment: Alignment.center,
        decoration: BoxDecoration(
          color: const Color.fromARGB(255, 130, 0, 216),
          borderRadius: BorderRadius.circular(10),
        ),
        child: Text(
          string,
          style: const TextStyle(
              color: Colors.white, fontWeight: FontWeight.w600, fontSize: 18),
        ),
      ),
    );
  }
}

class MyBehavior extends ScrollBehavior {
  Widget buildViewportChrome(
    BuildContext context,
    Widget child,
    AxisDirection axisDirection,
  ) {
    return child;
  }
}

Future<void> signOut() async {
  await Auth().signOut();
}
