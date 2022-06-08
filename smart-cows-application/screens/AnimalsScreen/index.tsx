import React from "react";
import { FontAwesome5 } from "@expo/vector-icons";
import { ScrollView, Text, View } from "react-native";
import dataInit, { names } from "../data";
import styles from "./styles";
import MapView, { Marker, Polyline, PROVIDER_GOOGLE } from "react-native-maps";
import { useAppSelector } from "../../redux-files/hooks";
import { LogBox } from 'react-native';
LogBox.ignoreLogs(['Warning: ...']); // Ignore log notification by message
LogBox.ignoreAllLogs();//Ignore all log notifications

export default function AnimalsScreen() {
  const { trace } = useAppSelector((state) => state.app);
  const data = dataInit();
  return data ? (
    <View style={styles.container}>
      <ScrollView
        style={styles.containerWrapper}
        showsVerticalScrollIndicator={false}
      >
        {data.map((element, index) => (
          <View style={styles.animalContainer} key={index}>
            <View style={styles.containerHeader}>
              <View style={styles.containerHeaderTwo}>
                <View style={styles.circle}></View>
                <View>
                  <Text style={styles.name}>{names[index]}</Text>
                  <Text>Temperature: {element.temperature}</Text>
                  <Text>Battery: {element.battery}%</Text>
                </View>
              </View>
              <View style={styles.checked}>
                <FontAwesome5 name="check" size={15} color="white" />
              </View>
            </View>
            <View style={styles.bottom}>
              <MapView
                provider={PROVIDER_GOOGLE}
                style={{ width: 300, height: 150 }}
                initialRegion={{
                  longitude: element.longitude,
                  latitude: element.latitude,
                  latitudeDelta: 0.003,
                  longitudeDelta: 0.003,
                }}
                mapType="standard"
                zoomEnabled={false}
                scrollEnabled={false}
              >
                <Polyline
                  coordinates={trace[index]}
                  strokeWidth={2}
                  strokeColor="black"
                />
                <Marker
                  key={index}
                  coordinate={{
                    latitude: element.latitude,
                    longitude: element.longitude,
                  }}
                />
              </MapView>
            </View>
          </View>
        ))}
      </ScrollView>
    </View>
  ) : (
    <></>
  );
}
