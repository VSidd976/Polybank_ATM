import { styled } from "@mui/material";
import "./App.css";
import BankCard from "./components/BankCard";
import { type ComponentPropsWithoutRef } from "react";
import { BANKS, TRANSACTION_COMPANY } from "./components/BankCard/consts";

const placeholderCard: ComponentPropsWithoutRef<typeof BankCard> = {
  ownerName: "Alexandr Stepanov",
  number: "4556000000000000",
  expDate: "10/39",
  bank: BANKS.POLY_BANK,
  transactionCompany: TRANSACTION_COMPANY.VISA,
  cvv: 123,
} as const;

function App() {
  return (
    <LayoutContainer>
      <MainContent>
        <BankCard {...placeholderCard} />
      </MainContent>
    </LayoutContainer>
  );
}

const LayoutContainer = styled("div")`
  min-height: 100vh;
  width: 100vw;
  display: flex;
  flex-direction: column;
`;

const MainContent = styled("main")`
  flex: 1;
  display: flex;
  background: #fff;
  justify-content: center;
  align-items: center;
`;

export default App;
