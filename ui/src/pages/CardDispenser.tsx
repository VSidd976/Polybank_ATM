import { Fade, styled } from "@mui/material";
import { useBoolean } from "@utils/hooks/useBoolean";
import BankCard_ from "@components/BankCard";
import BaseButton from "@components/Button/Button";
import { useRandomCard } from "@utils/hooks/useRandomCard";
import { useNavigate, useSearchParams } from "react-router-dom";
import { useCallback, useEffect } from "react";
import type { Card } from "@components/BankCard/consts";
import AtmAPI from "@api/AtmAPI";

const animationDurationSec = 3.5;

const useInsert = (
  card: Card,
): { isInserted: boolean; insertCard: () => void } => {
  const [isInserted, { on }] = useBoolean();
  const navigate = useNavigate();
  const insertCard = useCallback(async () => {
    on();
    await AtmAPI.of(card).insertCard();
    setTimeout(() => navigate("/pin"), animationDurationSec * 1_000);
  }, [navigate, on, card]);
  return { isInserted, insertCard };
};

const useReturning = (): boolean => {
  const [params] = useSearchParams();
  const navigate = useNavigate();
  const isLogout = params.get("logout") === "true";
  useEffect(() => {
    if (!isLogout) return;
    setTimeout(() => navigate("/"), animationDurationSec * 1_000);
  }, [isLogout]);
  return isLogout;
};

const CardDispenser = () => {
  const [card, generateNew] = useRandomCard();
  const { isInserted, insertCard } = useInsert(card);
  const isReturning = useReturning();
  return (
    <Container>
      <BankCard
        $isInserted={isInserted}
        $isReturning={isReturning}
        card={card}
      />
      <Fade in={!isInserted || isReturning}>
        <ButtonsContainer>
          <BaseButton
            onClick={generateNew}
            disabled={isReturning}
            txt={"Generate Credentials"}
          />
          <BaseButton
            onClick={insertCard}
            disabled={isReturning}
            txt={"Insert Card"}
          />
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

const BankCard = styled(BankCard_)<{
  $isInserted: boolean;
  $isReturning: boolean;
}>`
  z-index: 1;
  ${({ $isReturning }) =>
    $isReturning
      ? `animation: rotateAndFloat ${animationDurationSec}s ease-in reverse backwards;`
      : ""}
  ${({ $isInserted }) =>
    $isInserted
      ? `animation: rotateAndFloat ${animationDurationSec}s ease-in forwards;`
      : ""}

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
