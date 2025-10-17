import { Fade, styled } from "@mui/material";
import { useBoolean } from "@utils/hooks/useBoolean";
import BankCard_ from "@components/BankCard";
import {
  BANKS,
  TRANSACTION_COMPANY,
  type Card,
} from "@components/BankCard/consts";
import BaseButton from "@components/Button/Button";

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
      <BankCard $animate={isAnimate} card={placeholderCard} />
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
