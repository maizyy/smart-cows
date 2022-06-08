// @ts-nocheck
import { FontAwesome, FontAwesome5 } from "@expo/vector-icons";
import { createBottomTabNavigator } from "@react-navigation/bottom-tabs";
import { NavigationContainer, DefaultTheme } from "@react-navigation/native";
import { createNativeStackNavigator } from "@react-navigation/native-stack";
import * as React from "react";
import { Pressable, View, Text } from "react-native";
import ModalScreen from "../screens/ModalScreen";
import NotFoundScreen from "../screens/NotFoundScreen";
import MapScreen from "../screens/MapScreen";
import AnimalsScreen from "../screens/AnimalsScreen";
import UserScreen from "../screens/UserScreen";
import {
  RootStackParamList,
  RootTabParamList,
  RootTabScreenProps,
} from "../types";
import LinkingConfiguration from "./LinkingConfiguration";

export default function Navigation() {
  return (
    <NavigationContainer linking={LinkingConfiguration} theme={DefaultTheme}>
      <RootNavigator />
    </NavigationContainer>
  );
}

const Stack = createNativeStackNavigator<RootStackParamList>();

function RootNavigator() {
  return (
    <Stack.Navigator>
      <Stack.Screen
        name="Root"
        component={BottomTabNavigator}
        options={{ headerShown: false }}
      />
      <Stack.Screen
        name="NotFound"
        component={NotFoundScreen}
        options={{ title: "Oops!" }}
      />
      <Stack.Group screenOptions={{ presentation: "modal" }}>
        <Stack.Screen name="Modal" component={ModalScreen} />
      </Stack.Group>
    </Stack.Navigator>
  );
}

const BottomTab = createBottomTabNavigator<RootTabParamList>();

function BottomTabNavigator() {
  return (
    <BottomTab.Navigator
      initialRouteName="MapScreen"
      screenOptions={{
        tabBarStyle: { height: 60 },
      }}
    >
      <BottomTab.Screen
        name="MapScreen"
        component={MapScreen}
        options={({ navigation }: RootTabScreenProps<"MapScreen">) => ({
          title: "",
          headerTitle: () => null,
          headerTransparent: true,
          tabBarIcon: ({ focused }) => (
            <TabBarIcon
              name="map-marked-alt"
              color={focused ? "#79c3e0" : "grey"}
            />
          ),
          // headerRight: () => (
          //   <Pressable
          //     onPress={() => navigation.navigate("Modal")}
          //     style={({ pressed }) => ({
          //       opacity: pressed ? 0.5 : 1,
          //       backgroundColor: "white",
          //       borderRadius: 20,
          //       marginRight: 15,
          //       shadowColor: "#000",
          //       shadowOffset: {
          //         width: 0,
          //         height: 3,
          //       },
          //       shadowOpacity: 0.29,
          //       shadowRadius: 4.65,
          //       elevation: 7,
          //       marginTop: -15,
          //     })}
          //   >
          //     <FontAwesome
          //       name="info-circle"
          //       size={25}
          //       color="#79c3e0"
          //       style={{
          //         paddingVertical: 7,
          //         paddingHorizontal: 9,
          //       }}
          //     />
          //   </Pressable>
          // ),
        })}
      />
      <BottomTab.Screen
        name="AnimalsScreen"
        component={AnimalsScreen}
        options={{
          title: "",
          header: () => (
            <View
              style={{
                backgroundColor: "white",
                padding: 20,
                shadowColor: "#000",
                shadowOffset: {
                  width: 0,
                  height: 3,
                },
                shadowOpacity: 0.09,
                shadowRadius: 4.65,
                elevation: 7,
              }}
            >
              <Text
                style={{ fontSize: 25, lineHeight: 35, fontWeight: "bold" }}
              >
                Your Animals
              </Text>
              <Text style={{ opacity: 0.6 }}>
                Here you can take a look at your animals
              </Text>
            </View>
          ),
          tabBarIcon: ({ focused }) => (
            <TabBarIcon name="paw" color={focused ? "#79c3e0" : "grey"} />
          ),
        }}
      />
      <BottomTab.Screen
        name="UserScreen"
        component={UserScreen}
        options={{
          title: "",
          header: () => (
            <View
              style={{
                backgroundColor: "white",
                padding: 20,
                shadowColor: "#000",
                shadowOffset: {
                  width: 0,
                  height: 3,
                },
                shadowOpacity: 0.09,
                shadowRadius: 4.65,
                elevation: 7,
              }}
            >
              <Text
                style={{ fontSize: 25, lineHeight: 35, fontWeight: "bold" }}
              >
                Account
              </Text>
              <Text style={{ opacity: 0.6 }}>Your personal information</Text>
            </View>
          ),
          tabBarIcon: ({ focused }) => (
            <TabBarIcon
              name="house-user"
              color={focused ? "#79c3e0" : "grey"}
            />
          ),
        }}
      />
    </BottomTab.Navigator>
  );
}

function TabBarIcon(props: {
  name: React.ComponentProps<typeof FontAwesome5>["name"];
  color: string;
}) {
  return <FontAwesome5 size={30} style={{ marginBottom: -12 }} {...props} />;
}
