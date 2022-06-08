import { Dimensions, StyleSheet } from "react-native";

export default StyleSheet.create({
  container: {
    flex: 1,
    width: Dimensions.get("window").width,
    height: Dimensions.get("window").height,
  },
  containerWrapper: {
    paddingHorizontal: 20,
    paddingBottom: 20,
    display: "flex",
    flexDirection: "column",
  },
  animalContainer: {
    marginRight: 15,
    width: Dimensions.get("window").width - 45,
    display: "flex",
    height: 250,
    marginBottom: 15,
    backgroundColor: "white",
    borderRadius: 15,
    shadowColor: "#000",
    paddingVertical: 12,
    paddingHorizontal: 15,
    shadowOffset: {
      width: 0,
      height: 0,
    },
    shadowOpacity: 0.1,
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
});
