import { StyleSheet, Dimensions } from "react-native";

export default StyleSheet.create({
  container: {
    flex: 1,
    alignItems: "flex-start",
    justifyContent: "flex-start",
    paddingHorizontal: 20,
    paddingTop: 20,
  },
  topContainer: {
    width: "100%",
    flexDirection: "row",
    justifyContent: "space-between",
    alignItems: "center",
    backgroundColor: "white",
    paddingVertical: 20,
    paddingHorizontal: 25,
    borderRadius: 15,
    marginBottom: 15
  },
  circle: {
    width: 90,
    height: 90,
    borderRadius: 100,
    backgroundColor: "#dedede",
  },
  name: {
    fontSize: 21,
    fontWeight: "600",
    lineHeight: 25,
  },
  surname: {
    fontSize: 21,
    fontWeight: "600",
    lineHeight: 25,
    marginBottom: 15,
  },
  mail: {
    opacity: 0.5,
  },
  option: {
    borderRadius: 15,
    paddingVertical: 15,
    paddingHorizontal: 20,
    width: "100%",
    flexDirection: "row",
    justifyContent: "space-between",
    alignItems: "center",
    backgroundColor: "white",
    marginTop: 10,
  },
  optionText: {
    fontSize: 16,
    fontWeight: "500",
  },
});
