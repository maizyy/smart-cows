/* eslint-disable no-param-reassign */

import { createSlice } from "@reduxjs/toolkit";
import { SmartCowState } from "./interfaces";
import { appendData } from "./thunk";

const initialState: SmartCowState = {
  fetched_data: {
    0: [],
    1: [],
    2: [],
    3: [],
  },
  trace: {
    0: [],
    1: [],
    2: [],
    3: [],
  },
};

export const locationSlice = createSlice({
  name: "location",
  initialState,
  reducers: {},
  extraReducers: (builder) => {
    builder.addCase(appendData.fulfilled, (state, action) => {
      const id = action.payload?.cowId;
      const data = action.payload?.data;
      if (id && data) {
        state.fetched_data[id] = [...state.fetched_data[id], data];
        state.trace[id] = [
          ...state.fetched_data[id],
          { longitude: data.longitude, latitude: data.latitude },
        ];
      }
    });
  },
});

// eslint-disable-next-line no-empty-pattern
export const {} = locationSlice.actions;

export default locationSlice.reducer;
