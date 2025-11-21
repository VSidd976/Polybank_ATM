import BaseButton from "@components/Button/Button";
import { styled } from "@mui/material";
import { withProps } from "@utils/withProps";
import type { ReactElement, ReactNode } from "react";
import { useNavigate } from "react-router-dom";
import SendIcon from "@mui/icons-material/Send";
import InputIcon from "@mui/icons-material/Input";
import AccountBalanceIcon from "@mui/icons-material/AccountBalance";
import PaymentsIcon from "@mui/icons-material/Payments";

const BUTTONS: { txt: string; navigate: string; startIcon?: ReactNode }[] = [
  {
    txt: "Account info",
    navigate: "/main/account-info",
    startIcon: <AccountBalanceIcon />,
  },
  { txt: "Cash out", navigate: "/main/cash-out", startIcon: <PaymentsIcon /> },
  { txt: "Put money", navigate: "/main/add-money", startIcon: <InputIcon /> },
  {
    txt: "Transfer money",
    navigate: "/main/transfer",
    startIcon: <SendIcon />,
  },
] as const;

const MainScreen = (): ReactElement => {
  const navigate = useNavigate();
  return (
    <Container>
      <ButtonsGrid>
        {BUTTONS.map((b, i) => (
          <MenuButton
            key={b.txt + i}
            {...b}
            onClick={() => navigate(b.navigate)}
          />
        ))}
      </ButtonsGrid>
    </Container>
  );
};

export default MainScreen;

const MenuButton = styled(
  withProps(BaseButton, { variant: "rectangular" } as const),
)`
  display: flex;
  align-items: center;
  gap: 12px;
  justify-content: center;
  padding: 16px;
  max-width: 400px;
  width: 100%;
  svg {
    font-size: 28px;
  }
  span[data-role="txt"] {
    font-size: 28px;
  }
`;

const ButtonsGrid = styled("div")`
  display: grid;
  flex: 1;

  padding: 25px;
  grid-template-columns: repeat(2, 1fr);
  grid-auto-rows: auto;
  flex-wrap: wrap;

  & > *:nth-of-type(2n + 1) {
    justify-self: end;
  }

  & > *:nth-of-type(2n) {
    justify-self: start;
  }
  gap: 35px;
`;

const Container = styled("div")`
  width: 100%;
  display: flex;
  max-width: 100vw;
  align-items: center;
  align-self: center;
  justify-content: space-around;
`;
