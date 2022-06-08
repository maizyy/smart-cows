export interface SmartCowState {
  fetched_data: {
    [key: number]: LocationProps[];
  };
  trace: { [key: number]: TraceProps[] };
}

export interface LocationProps {
  longitude: number;
  latitude: number;
  timestamp: number;
}

export interface TraceProps {
  longitude: number;
  latitude: number;
}
