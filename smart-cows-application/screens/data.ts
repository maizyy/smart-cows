import { useEffect, useState } from "react";
import * as firebase from "@firebase/database";
import { app } from "../config";
import { useAppDispatch } from "../redux-files/hooks";
import { appendData } from "../redux-files/thunk";

interface AnimalData {
  battery: number;
  latitude: number;
  longitude: number;
  temperature: number;
  timestamp: number;
}

export default function dataInit() {
  const dispatch = useAppDispatch();
  const [animals, setAnimals] = useState<AnimalData[]>([]);
  useEffect(() => {
    setInterval(() => {
      const db = firebase.getDatabase(app);
      const starCountRef = firebase.ref(db);
      firebase.onValue(starCountRef, (snapshot) => {
        const data = snapshot.val();
        const processedData: AnimalData[] = Object.values(data);
        processedData.pop()
        console.log(processedData)
        setAnimals([...processedData]);
      });
    }, 30000);
  }, []);

  useEffect(() => {
    for (let i = 0; i < animals.length; i++) {
      dispatch(
        appendData({
          data: {
            timestamp: animals[i].timestamp,
            latitude: animals[i].latitude,
            longitude: animals[i].longitude,
          },
          cowId: i,
        })
      );
    }
  }, [animals]);

  return animals;
}

export const names = ["Clarabelle", "Nellie", "Buttercup", "Guinness"];

export const home = {
  latitude: 8.99932,
  longitude: 13.58438,
  latitudeDelta: 0.012,
  longitudeDelta: 0.012,
};
