// ignore_for_file: library_private_types_in_public_api, camel_case_types, unused_local_variable, unused_field, file_names

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class DoctorsPage extends StatefulWidget {
  const DoctorsPage({super.key});

  @override
  _DoctorsPageState createState() => _DoctorsPageState();
}

class _DoctorsPageState extends State<DoctorsPage> {
  final List<PhotoTextContainer> items = [
    PhotoTextContainer(
      photoUrl:
          'https://scontent.fcai21-4.fna.fbcdn.net/v/t39.30808-6/292736513_3843473745878303_1653483658805673217_n.jpg?_nc_cat=101&ccb=1-7&_nc_sid=09cbfe&_nc_eui2=AeGZBeQwyzvEfDuCmz_NeW2-rt7pUPjTD3uu3ulQ-NMPewDkfxkdJUt1wtN5s83EZfqeS1lirJ55W-wcc8zquMG4&_nc_ohc=a9upD8A0VSIAX-4jl9y&_nc_ht=scontent.fcai21-4.fna&oh=00_AfCE3poPx1xEZ_EbUdaee4i1340U2aY-Aa96qgp_J-sKyA&oe=64EFFC1D',
      text: 'Ahmed Gamal',
    ),
    PhotoTextContainer(
      photoUrl:
          'https://scontent.fcai21-4.fna.fbcdn.net/v/t1.6435-9/125220753_3784575351593939_312179511032188127_n.jpg?_nc_cat=109&ccb=1-7&_nc_sid=174925&_nc_eui2=AeFySWDJExWpSRoLXfPcZXiMj6e6xpdrZgKPp7rGl2tmAsw4Wdd0js_DzdgdNLF2GMNLKHLPbE6aVPVeuavcvN_y&_nc_ohc=f8hzDu_NkxEAX8ksgwd&_nc_ht=scontent.fcai21-4.fna&oh=00_AfA3SuWooVUO9wlwUczklMyfeeENvfA2tNRU_-QzFcWqgw&oe=65120C26',
      text: 'Ziad Hany',
    ),
    PhotoTextContainer(
      photoUrl:
          'https://scontent.fcai21-3.fna.fbcdn.net/v/t39.30808-6/294626395_2408204925986577_1752211329768885713_n.jpg?_nc_cat=105&ccb=1-7&_nc_sid=09cbfe&_nc_eui2=AeGHIHMNAu_6BK6nO9hjjd-Vqr3a1i8ND12qvdrWLw0PXRtI715eQ8_dEJEKs-7y_9Lu7R_06-VI2TDtV0MrYwq8&_nc_ohc=hEZ5jF9kaJ8AX-jMq6c&_nc_ht=scontent.fcai21-3.fna&oh=00_AfCCPOcXxJKnpxd4bNjcQMNSJMGTh0jzIB7OnQwgyWPM3g&oe=64F075E3',
      text: 'Myar Hany',
    ),
    PhotoTextContainer(
      photoUrl:
          'https://scontent.fcai21-4.fna.fbcdn.net/v/t39.30808-6/309660973_1963380900538712_1431220135011464614_n.jpg?_nc_cat=109&ccb=1-7&_nc_sid=09cbfe&_nc_eui2=AeHDQhkumLp0UDnjzytLz9Vi1zhqbYjqDjzXOGptiOoOPC80vBP-vCa2_7KTcCiTIE0MkxIRkxF0sLyFtfERWcyd&_nc_ohc=bSEkJYiFYbsAX-WJivL&_nc_ht=scontent.fcai21-4.fna&oh=00_AfC4ZRFUoNsGEQhtNtd7S2tDd4jg88sbbxC4jCl2zmHlfQ&oe=64EF6D94',
      text: 'Rana Yasser',
    ),
    PhotoTextContainer(
      photoUrl:
          'https://scontent.fcai21-3.fna.fbcdn.net/v/t39.30808-6/324906173_5834270069996040_6703405373877334264_n.jpg?_nc_cat=110&ccb=1-7&_nc_sid=09cbfe&_nc_eui2=AeHLJGDX-dVHMx4XCHHCfqVWNsBtw151-RQ2wG3DXnX5FLmlAAW_IUGH8bJnR1MXA7SzYMSDsLz6NYHJADNw5IgG&_nc_ohc=s8fonqS5iusAX-xRivg&_nc_ht=scontent.fcai21-3.fna&oh=00_AfC5cuvMw77d_zFmIDAxFCipDDrd2Pc3MFz1yK8but3dbw&oe=64F07E4B',
      text: 'Peter Hany',
    ),
    PhotoTextContainer(
      photoUrl:
          'https://scontent.fcai21-4.fna.fbcdn.net/v/t39.30808-6/352386150_764534688698494_4281769595460191731_n.jpg?_nc_cat=103&ccb=1-7&_nc_sid=09cbfe&_nc_eui2=AeHggJojb1kb9WWKf-WM2szYkbohoDLEnB-RuiGgMsScHy24Xf5pc813oXwo3MxQrq7W1hhd_xLU_RY7RwUGHiu8&_nc_ohc=DtYnOiO9RScAX9gdgi0&_nc_ht=scontent.fcai21-4.fna&oh=00_AfAXBzZoklLvObIbWcRwzpSW6EjnpMLR_Ccat3Il9M5MlQ&oe=64F0798E',
      text: 'Mostafa Maraey',
    ),
    // Add more items as needed
  ];
  @override
  Widget build(BuildContext context) {
    double w = MediaQuery.of(context).size.width;
    return Scaffold(
        backgroundColor: Colors.white,
        appBar: AppBar(
          backgroundColor: Colors.white,
          elevation: 50,
          centerTitle: true,
          shadowColor: Colors.black.withOpacity(.5),
          title: Text(
            'OUR TEAM',
            style: TextStyle(
                color: Colors.black.withOpacity(.7),
                fontWeight: FontWeight.w600,
                letterSpacing: 1),
          ),
          leading: IconButton(
            icon: Icon(
              Icons.arrow_back,
              color: Colors.black.withOpacity(.8),
            ),
            onPressed: () => Navigator.maybePop(context),
          ),
          systemOverlayStyle: SystemUiOverlayStyle.dark,
        ),
        body: ListView.builder(
          itemCount: items.length,
          itemBuilder: (context, index) {
            return PhotoTextContainer(
              photoUrl: items[index].photoUrl,
              text: items[index].text,
            );
          },
        ));
  }
}

class PhotoTextContainer extends StatelessWidget {
  final String photoUrl;
  final String text;

  PhotoTextContainer({required this.photoUrl, required this.text});

  @override
  Widget build(BuildContext context) {
    return Container(
      margin: EdgeInsets.all(8.0),
      child: Column(
        children: [
          Container(
            height: 300, // Set the desired square size
            width: 300, // Set the desired square size
            decoration: BoxDecoration(
              shape: BoxShape.rectangle, // Make it a circular container
              image: DecorationImage(
                image: NetworkImage(photoUrl),
                fit:
                    BoxFit.cover, // Make the image cover the circular container
              ),
            ),
          ),
          Container(
              padding: EdgeInsets.all(8.0),
              decoration: BoxDecoration(
                color: Color.fromARGB(255, 69, 0, 159),
                borderRadius: BorderRadius.only(
                  bottomLeft: Radius.circular(10.0),
                  bottomRight: Radius.circular(10.0),
                ),
              ),
              child: Center(
                  child: Text(
                text,
                style: TextStyle(
                  color: Colors.white,
                  fontSize: 18,
                  fontWeight: FontWeight.bold,
                  fontFamily: 'Pacifico', // Custom font family
                ),
              ))),
        ],
      ),
    );
  }
}
