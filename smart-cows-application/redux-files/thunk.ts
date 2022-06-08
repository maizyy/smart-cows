import { createAsyncThunk } from "@reduxjs/toolkit";
import { LocationProps } from "./interfaces";

export const appendData = createAsyncThunk(
  "appendData",
  async ({ data, cowId }: { data: LocationProps; cowId: number }) => {
    try {
      return { data, cowId };
    } catch (e) {
      console.error(e);
    }
  }
);
