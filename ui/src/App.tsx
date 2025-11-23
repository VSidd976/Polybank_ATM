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
import CashOut from "@pages/CashOut";
import Transfer from "@pages/Transfer";
import ProtectedRoute from "@utils/ProtectedRoute";
import AccountInfo from "@pages/AccountInfo";
import Deposit from "@pages/Deposit";
import SuccessfulOperation from "@pages/SuccessfulOperation";

function App() {
  return (
    <ThemeProvider theme={themeOptions} defaultMode="dark">
      <LayoutContainer>
        <BrowserRouter>
          <Header />
          <MainContent>
            <Routes>
              <Route index element={<CardDispenser />} />
              <Route path="/pin" element={<Pin />} />
              <Route
                path="/main"
                element={
                  <ProtectedRoute>
                    <MainScreen />
                  </ProtectedRoute>
                }
              />
              <Route
                path="/main/add-money"
                element={
                  <ProtectedRoute>
                    <AddMoney />
                  </ProtectedRoute>
                }
              />
              <Route
                path="/main/cash-out"
                element={
                  <ProtectedRoute>
                    <CashOut />
                  </ProtectedRoute>
                }
              />
              <Route
                path="/main/transfer"
                element={
                  <ProtectedRoute>
                    <Transfer />
                  </ProtectedRoute>
                }
              />
              <Route
                path="/main/account-info"
                element={
                  <ProtectedRoute>
                    <AccountInfo />
                  </ProtectedRoute>
                }
              />
              <Route
                path="/main/deposits"
                element={
                  <ProtectedRoute>
                    <Deposit />
                  </ProtectedRoute>
                }
              />
              <Route
                path="/main/success"
                element={
                  <ProtectedRoute>
                    <SuccessfulOperation />
                  </ProtectedRoute>
                }
              />
            </Routes>
          </MainContent>
        </BrowserRouter>
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
  position: relative;
  background:
    linear-gradient(135deg, rgba(255 255 255 / 0.08), rgba(255 255 255 / 0)),
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
  background-color: ${({ theme }) => theme.palette.background.paper};

  );
`;

export default App;
