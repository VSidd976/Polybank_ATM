import { styled } from "@mui/material";
import "./App.css";
import BankCard_ from "./components/BankCard";
import { type ComponentPropsWithoutRef } from "react";
import { BANKS, TRANSACTION_COMPANY } from "./components/BankCard/consts";
import { useBoolean } from "./utils/hooks/useBoolean";

const placeholderCard: ComponentPropsWithoutRef<typeof BankCard_> = {
  ownerName: "Alexandr Stepanov",
  number: "4556000000000000",
  expDate: "10/39",
  bank: BANKS.POLY_BANK,
  transactionCompany: TRANSACTION_COMPANY.VISA,
  cvv: 123,
} as const;

function App() {
  const [animate, { toggle }] = useBoolean();
  return (
    <LayoutContainer>
      <MainContent>
        <BankCard $animate={animate} {...placeholderCard} />
        <button onClick={toggle}>click me</button>
      </MainContent>
    </LayoutContainer>
  );
}

const BankCard = styled(BankCard_)<{ $animate: boolean }>`
  ${({ $animate }) =>
    $animate ? `animation: rotateAndFloat 3.5s ease-in forwards;` : ""}

  @keyframes rotateAndFloat {
    0% {
      transform: rotate(0deg) translateX(0);
      opacity: 1;
    }
    25% {
      transform: rotate(90deg) translateX(0);
      opacity: 1;
    }
    50% {
      transform: rotate(90deg) translateX(0);
      opacity: 1;
    }
    100% {
      transform: rotate(90deg) translateX(-150vh);
      opacity: 0;
    }
  }
`;

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
