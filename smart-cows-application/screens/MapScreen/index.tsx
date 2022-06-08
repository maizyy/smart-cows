import { RootTabScreenProps } from "../../types";
import MapView, { Circle, Marker, PROVIDER_GOOGLE } from "react-native-maps";
import styles from "./styles";
import { Pressable, ScrollView, Text, View } from "react-native";
import { FontAwesome5 } from "@expo/vector-icons";
import dataInit, { home, names } from "../data";
import React, { createRef, useEffect, useState } from "react";
import * as Location from "expo-location";
import MapViewDirections from "react-native-maps-directions";
import { LogBox } from 'react-native';
LogBox.ignoreLogs(['Warning: ...']); // Ignore log notification by message
LogBox.ignoreAllLogs();//Ignore all log notifications

export default function MapScreen({
  navigation,
}: RootTabScreenProps<"MapScreen">) {
  const [selectedCow, setSelectedCow] = useState<number | null>(null);
  const [currentPosition, setCurrentPosition] = useState<{
    latitude: number;
    longitude: number;
  }>();

  const [currentPositionRadius, setCurrentPositionRadius] = useState<number>();
  const circleSmall = createRef<Circle>();
  const circleMedium = createRef<Circle>();
  const circleBig = createRef<Circle>();
  const data = dataInit();

  const getPermission = async () => {
    const { status } = await Location.requestForegroundPermissionsAsync();
    if (status !== "granted") {
      alert("Permission to access location was denied");
      return;
    }
  };

  useEffect(() => {
    getPermission();
    setInterval(async () => {
      let location = await Location.getCurrentPositionAsync({});

      setCurrentPosition({
        latitude: location.coords.latitude,
        longitude: location.coords.longitude,
      });

      setCurrentPositionRadius(location.coords.altitude || 0);
    }, 500);
  }, []);

  useEffect(() => {
    circleMedium.current?.setNativeProps({
      fillColor: "#79c3e050",
      strokeColor: "#79c3e050",
    });
    circleSmall.current?.setNativeProps({
      fillColor: "#79c3e0",
      strokeColor: "#79c3e0",
    });
    circleBig.current?.setNativeProps({
      fillColor: "#79c3e050",
      strokeColor: "#79c3e050",
    });
  }, [currentPosition]);

  return (
    <View style={styles.container}>
      {currentPosition && currentPositionRadius !== undefined && (
        <MapView
          provider={PROVIDER_GOOGLE}
          style={styles.mapStyle}
          initialRegion={{
            ...home,
            longitude: currentPosition.longitude,
            latitude: currentPosition.latitude,
          }}
          mapType="standard"
        >
          {data.map(
            (element, index) =>
              data && (
                <Marker
                  key={index}
                  coordinate={{
                    latitude: element.latitude,
                    longitude: element.longitude,
                  }}
                  title={names[index]}
                >
                  <View style={styles.marker} />
                </Marker>
              )
          )}
          <Circle
            ref={circleSmall}
            center={{
              latitude: currentPosition.latitude,
              longitude: currentPosition.longitude,
            }}
            radius={20}
            style={{ position: "absolute", zIndex: 2 }}
          />
          <Circle
            ref={circleMedium}
            center={{
              latitude: currentPosition.latitude,
              longitude: currentPosition.longitude,
            }}
            radius={35}
            style={{ position: "absolute", zIndex: 2 }}
          />
          <Circle
            ref={circleBig}
            center={{
              latitude: currentPosition.latitude,
              longitude: currentPosition.longitude,
            }}
            radius={currentPositionRadius}
            style={{ position: "absolute", zIndex: 2 }}
          />
          {selectedCow !== null && data && data[selectedCow] && (
            <MapViewDirections
              origin={{
                latitude: currentPosition.latitude,
                longitude: currentPosition.longitude,
              }}
              destination={{
                latitude: data[selectedCow].latitude,
                longitude: data[selectedCow].longitude,
              }}
              mode="WALKING"
              strokeWidth={3}
              apikey="AIzaSyAj1Dso7ymhGBcA0JRXNZ-Ag3AI5vQyk0c"
            />
          )}
        </MapView>
      )}
      <ScrollView
        horizontal
        style={styles.bottomContainerWrapper}
        showsHorizontalScrollIndicator={false}
      >
        {data.map(
          (element, index) =>
            data && (
              <View style={styles.animalContainer} key={index}>
                <View style={styles.containerHeader}>
                  <View style={styles.containerHeaderTwo}>
                    <View style={styles.circle}></View>
                    <View>
                      <Text style={styles.name}>{names[index]}</Text>
                      <Text>Temperature: {element.temperature}</Text>
                    </View>
                  </View>
                  {selectedCow !== null && names[selectedCow] === names[index] && (
                    <View style={styles.checked}>
                      <FontAwesome5 name="check" size={15} color="white" />
                    </View>
                  )}
                </View>
                <View style={styles.bottom}>
                  <Text style={styles.coordinates}>
                    {`Longitute:\n`}
                    <Text style={styles.coordinatesNumber}>
                      {element.longitude}
                    </Text>
                  </Text>
                  <Text style={styles.coordinates}>
                    {`Latitude:\n`}
                    <Text style={styles.coordinatesNumber}>
                      {element.latitude}
                    </Text>
                  </Text>
                  {!(
                    selectedCow !== null && names[selectedCow] === names[index]
                  ) && (
                    <Pressable
                      style={styles.button}
                      onPress={() => setSelectedCow(index)}
                    >
                      <Text style={styles.buttonText}>Create route</Text>
                    </Pressable>
                  )}
                  {selectedCow !== null &&
                    names[selectedCow] === names[index] && (
                      <View style={styles.simpleButton} />
                    )}
                </View>
              </View>
            )
        )}
      </ScrollView>
    </View>
  );
}
