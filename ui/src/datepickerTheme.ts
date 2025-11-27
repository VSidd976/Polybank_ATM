import { createTheme, type ThemeOptions } from "@mui/material";
import { themeOptions } from "./theme";

export const datePickerTheme: ThemeOptions = createTheme({
  palette: {
    ...themeOptions.palette,
    text: {
      primary: "white",
      secondary: "white",
      disabled: "grey",
    },
  },
});
