import { Fade, styled } from "@mui/material";
import { useBoolean } from "@utils/hooks/useBoolean";
import BankCard_ from "@components/BankCard";
import {
  BANKS,
  TRANSACTION_COMPANY,
  type Card,
} from "@components/BankCard/consts";
import BaseButton from "@components/Button/Button";
import { useCallback, useState } from "react";
import { randomInRange } from "@utils/randomInRange";

const defaultFields: Pick<Card, "bank" | "transactionCompany"> = {
  bank: BANKS.POLY_BANK,
  transactionCompany: TRANSACTION_COMPANY.VISA,
} as const;

const OWNERS = ["Alexandr Stepanov"];

function generateCard(): Card {
  return {
    ...defaultFields,
    number: `${randomInRange(4556_0000_0000_0000, 4556_9999_9999_9999)}`,
    expDate: `${randomInRange(1, 12).toString().padStart(2, "0")}/${randomInRange(25, 35).toString().padStart(2, "0")}`,
    ownerName: OWNERS[randomInRange(0, OWNERS.length - 1)],
    cvv: randomInRange(0, 999).toString().padStart(3, "0"),
  };
}

const useRandomCard = () => {
  const [card, setCard] = useState(generateCard());
  const generateNew = useCallback(() => setCard(generateCard), [setCard]);
  return [card, generateNew] as const;
};

const CardDispenser = () => {
  const [isAnimate, { toggle }] = useBoolean();
  const [card, generateNew] = useRandomCard();
  return (
    <Container>
      <BankCard $animate={isAnimate} card={card} />
      <Fade in={!isAnimate}>
        <ButtonsContainer>
          <BaseButton onClick={generateNew} txt={"Generate Credentials"} />
          <BaseButton onClick={toggle} txt={"InsertCard"} />
        </ButtonsContainer>
      </Fade>
    </Container>
  );
};

export default CardDispenser;

const Container = styled("div")`
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  flex: 1;
  gap: 25px;
`;

const ButtonsContainer = styled("div")`
  display: flex;
  gap: 15px;
`;

const BankCard = styled(BankCard_)<{ $animate: boolean }>`
  z-index: 1;
  ${({ $animate }) =>
    $animate ? `animation: rotateAndFloat 3.5s ease-in forwards;` : ""}

  @keyframes rotateAndFloat {
    0% {
      transform: translate(0, 0) rotate(0deg);
      opacity: 1;
    }
    15% {
      transform: translate(0, -120px) rotate(0deg);
      opacity: 1;
    }
    30% {
      transform: translate(20px, -120px) rotate(90deg);
      opacity: 1;
    }
    100% {
      transform: translate(40px, -150vh) rotate(90deg);
      opacity: 0;
    }
  }
`;
