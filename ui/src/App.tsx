import { styled, ThemeProvider } from "@mui/material";
import "./App.css";
import { themeOptions } from "./theme";
import Header from "@components/Header";
import CardDispenser from "@pages/CardDispenser";
import Pin from "@pages/Pin";
import { BrowserRouter, Route, Routes } from "react-router-dom";
import { ToastContainer } from "react-toastify";
import MainScreen from "@pages/MainScreen";
import AddMoney from "@pages/AddMoney";

function App() {
  return (
    <ThemeProvider theme={themeOptions} defaultMode="dark">
      <LayoutContainer>
        <Header />
        <MainContent>
          <BrowserRouter>
            <Routes>
              <Route path="/" element={<CardDispenser />} />
              <Route path="/pin" element={<Pin />} />
              <Route path="/main" element={<MainScreen />} />
              <Route path="/main/add-money" element={<AddMoney />} />
            </Routes>
          </BrowserRouter>
        </MainContent>
      </LayoutContainer>
      <ToastContainer />
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
