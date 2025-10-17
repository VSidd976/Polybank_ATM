import { createTheme, type ThemeOptions } from "@mui/material";

export const themeOptions: ThemeOptions = createTheme({
  palette: {
    mode: "light",
    primary: {
      100: "#B2DFDB",
      300: "#4DB6AC",
      light: "#00A896",
      main: "#028090",
      dark: "#1A3D3E",
      contrastText: "#FFFCFB",
    },
    secondary: {
      main: "#f50057",
    },
    text: {
      primary: "#1A3D3E",
      secondary: "#1A3D3E",
      disabled: "#1c3b3c",
    },
  },
});
