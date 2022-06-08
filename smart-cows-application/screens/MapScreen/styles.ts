import { StyleSheet, Dimensions } from "react-native";

export default StyleSheet.create({
  container: {
    flex: 1,
    alignItems: "center",
    justifyContent: "center",
  },
  title: {
    fontSize: 20,
    fontWeight: "bold",
  },
  mapStyle: {
    width: Dimensions.get("window").width,
    height: Dimensions.get("window").height,
  },
  bottomContainerWrapper: {
    position: "absolute",
    bottom: 0,
    display: "flex",
    flexDirection: "row",
    overflow: "hidden",
    width: "100%",
    height: 160,
    paddingHorizontal: 10,
  },
  animalContainer: {
    marginRight: 15,
    width: Dimensions.get("window").width - 45,
    display: "flex",
    height: 140,
    backgroundColor: "white",
    borderRadius: 15,
    shadowColor: "#000",
    paddingVertical: 12,
    paddingHorizontal: 15,
    shadowOffset: {
      width: 0,
      height: 0,
    },
    shadowOpacity: 0.29,
    shadowRadius: 4.65,
    elevation: 6,
    marginTop: 10,
  },
  containerHeader: {
    display: "flex",
    flexDirection: "row",
    alignItems: "flex-start",
    justifyContent: "space-between",
    marginBottom: 20,
  },
  containerHeaderTwo: {
    display: "flex",
    flexDirection: "row",
    alignItems: "center",
  },
  circle: {
    height: 45,
    width: 45,
    backgroundColor: "#dedede",
    borderRadius: 30,
    marginRight: 15,
  },
  name: {
    fontSize: 18,
    lineHeight: 25,
    fontWeight: "600",
  },
  checked: {
    backgroundColor: "#79c3e0",
    padding: 5,
    borderRadius: 20,
  },
  bottom: {
    display: "flex",
    flexDirection: "row",
    alignItems: "center",
    justifyContent: "space-between",
  },
  button: {
    width: 120,
    borderColor: "#a2d6ea",
    borderWidth: 2.5,
    height: 45,
    alignItems: "center",
    justifyContent: "center",
    borderRadius: 15,
  },
  simpleButton: {
    width: 120,
    height: 45,
  },
  buttonText: {
    color: "#a2d6ea",
    fontWeight: "800",
  },
  coordinates: {
    fontSize: 12,
    lineHeight: 19,
  },
  coordinatesNumber: {
    fontSize: 14,
  },
  marker: {
    height: 22,
    width: 22,
    borderRadius: 20,
    borderColor: "white",
    backgroundColor: "red",
    borderWidth: 2,
  },
});
