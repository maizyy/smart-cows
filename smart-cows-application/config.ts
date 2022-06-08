import { initializeApp } from "@firebase/app";

const firebaseConfig = {
    apiKey: "AIzaSyCGC2LY_IcuagL7AHCQe5gZEj6su8-KJf8",
    authDomain: "fluent-limiter-349320.firebaseapp.com",
    databaseURL: "https://fluent-limiter-349320-default-rtdb.europe-west1.firebasedatabase.app",
    projectId: "fluent-limiter-349320",
    storageBucket: "fluent-limiter-349320.appspot.com",
    messagingSenderId: "1033634120245",
    appId: "1:1033634120245:web:7c84cbcc8d2dc4c4c7277c",
    measurementId: "G-V0WYWCXHZ2"
  };

export const app = initializeApp(firebaseConfig);