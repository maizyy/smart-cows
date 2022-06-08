import React, { useState } from "react";
import { View, Text, Switch } from "react-native";
import { RootTabScreenProps } from "../../types";
import styles from "./styles";
import * as Location from "expo-location";
import { LogBox } from 'react-native';
LogBox.ignoreLogs(['Warning: ...']); // Ignore log notification by message
LogBox.ignoreAllLogs();//Ignore all log notifications

export default function UserScreen({
  navigation,
}: RootTabScreenProps<"UserScreen">) {
  const [geolocation, setGeolocation] = useState(true);
  const [notification, setNotifications] = useState(false);

  const getPermission = async () => {
    const { status } = await Location.requestForegroundPermissionsAsync();
    if (status !== "granted") {
      alert("Permission to access location was denied");
      return;
    }
  };
  return (
    <View style={styles.container}>
      <View style={styles.topContainer}>
        <View>
          <Text style={styles.name}>Michał</Text>
          <Text style={styles.surname}>Kowalski</Text>
          <Text style={styles.mail}>mkowalski@gmail.com</Text>
        </View>
        <View style={styles.circle} />
      </View>
      <View style={styles.option}>
        <Text style={styles.optionText}>Enable notifications</Text>
        <Switch
          value={notification}
          onValueChange={(value) => {
            setNotifications(value);
            if (value)  getPermission();
          }}
          trackColor={{ false: "#767577", true: "#79c3e0" }}
        />
      </View>
      <View style={styles.option}>
        <Text style={styles.optionText}>Enable geolocation</Text>
        <Switch
          value={geolocation}
          onValueChange={setGeolocation}
          trackColor={{ false: "#767577", true: "#79c3e0" }}
        />
      </View>
    </View>
  );
}
