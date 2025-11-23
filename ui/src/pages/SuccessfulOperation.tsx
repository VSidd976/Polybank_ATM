import BaseButton from "@components/Button/Button";
import { Title } from "@components/Title/title";
import { styled } from "@mui/material";
import type { ReactElement } from "react";
import CheckCircleIcon_ from "@mui/icons-material/CheckCircle";
import { BackButton } from "@components/Button/BackButton";
import { useBoolean } from "@utils/hooks/useBoolean";

const SuccessfulOperation = (): ReactElement => {
  const [isDisabled, disabled] = useBoolean();
  return (
    <Container>
      <BackButton disabled={isDisabled} />
      <Title>Operation successful!</Title>
      <CheckCircleIcon />
      <Title>Want to print a receipt?</Title>
      <Buttons>
        <BaseButton txt="Print" disabled={isDisabled} onClick={disabled.on} />
      </Buttons>
    </Container>
  );
};

export default SuccessfulOperation;

const CheckCircleIcon = styled(CheckCircleIcon_)`
  color: ${({ theme }) => theme.palette.secondary.main};
  font-size: 64px;
  animation: 1.5s appear ease forwards;
  opacity: 0;
  @keyframes appear {
    0% {
      opacity: 0;
    }

    100% {
      opacity: 1;
    }
  }
`;

const Buttons = styled("div")`
  display: flex;
  gap: 12px;
  animation: 1.5s appear ease forwards;
  opacity: 0;
  @keyframes appear {
    0% {
      opacity: 0;
    }

    100% {
      opacity: 1;
    }
  }
`;

const Container = styled("div")`
  width: 100%;
  display: flex;
  max-width: 100vw;
  flex-direction: column;
  gap: 12px;
  align-items: center;
  align-self: center;
  justify-content: space-around;
`;
