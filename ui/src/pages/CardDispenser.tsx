import { Fade, styled } from "@mui/material";
import { useBoolean } from "@utils/hooks/useBoolean";
import BankCard from "@components/BankCard";
import {
  BANKS,
  TRANSACTION_COMPANY,
  type Card,
} from "@components/BankCard/consts";
import BaseButton from "@components/Button/Button";
import InOutContainer from "@components/Dispenser/InOutContainer";

const placeholderCard: Card = {
  ownerName: "Alexandr Stepanov",
  number: "4556000000000000",
  expDate: "10/39",
  bank: BANKS.POLY_BANK,
  transactionCompany: TRANSACTION_COMPANY.VISA,
  cvv: 123,
} as const;

const CardDispenser = () => {
  const [isAnimate, { toggle }] = useBoolean();
  return (
    <Container>
      <InOutContainer isAnimated={isAnimate}>
        <BankCard card={placeholderCard} />
      </InOutContainer>
      <Fade in={!isAnimate}>
        <ButtonsContainer>
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

const ButtonsContainer = styled("div")``;
