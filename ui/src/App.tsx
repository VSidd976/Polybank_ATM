import { styled, ThemeProvider } from "@mui/material";
import "./App.css";
import { themeOptions } from "./theme";
import Header from "@components/Header";
import CardDispenser from "@pages/CardDispenser";

function App() {
  return (
    <ThemeProvider theme={themeOptions}>
      <LayoutContainer>
        <Header />
        <MainContent>
          <CardDispenser />
        </MainContent>
      </LayoutContainer>
    </ThemeProvider>
  );
}

const LayoutContainer = styled("div")`
  min-height: 100vh;
  width: 100vw;
  display: flex;
  flex-direction: column;
`;

const MainContent = styled("main")`
  display: flex;
  flex: 1;
  background:
    linear-gradient(135deg, rgba(255 255 255 / 0.1), rgba(255 255 255 / 0)),
    repeating-linear-gradient(
      90deg,
      rgba(255 255 255 / 0.05),
      rgba(255 255 255 / 0.05) 1px,
      transparent 1px,
      transparent 40px
    ),
    repeating-linear-gradient(
      0deg,
      rgba(255 255 255 / 0.05),
      rgba(255 255 255 / 0.05) 1px,
      transparent 1px,
      transparent 40px
    );
  background-color: #1a2121;
`;

export default App;
