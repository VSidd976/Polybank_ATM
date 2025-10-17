import { createTheme, type ThemeOptions } from "@mui/material";

export const themeOptions: ThemeOptions = createTheme({
  palette: {
    background: {
      paper: "#141414",
    },
    mode: "light",
    primary: {
      main: "#6320EE",
      light: "#8075FF",
      contrastText: "#F8F0FB",
      dark: "#421d86",
    },
    secondary: {
      main: "#01B2AC",
      dark: "#02707E",
      light: "#00DBC4",
      contrastText: "#F8F0FB",
    },
    text: {
      primary: "#211A1D",
      secondary: "#FFFCFB",
      disabled: "#CBCBCB",
    },
  },
});
