import BaseButton from "@components/Button/Button";
import { styled } from "@mui/material";
import { withProps } from "@utils/withProps";
import type { ReactElement } from "react";
import { useNavigate } from "react-router-dom";

const BUTTONS: { txt: string; navigate: string }[] = [
  { txt: "Account info", navigate: "/main/account-info" },
  { txt: "Put money", navigate: "/main/add-money" },
  { txt: "Cash out", navigate: "/main/cash-out" },
  { txt: "Transfer", navigate: "/main/transfer" },
  { txt: "Logout", navigate: "/?logout=true" },
] as const;

const MainScreen = (): ReactElement => {
  const navigate = useNavigate();
  return (
    <Container>
      <ButtonsGrid>
        {BUTTONS.map((b, i) => (
          <MenuButton
            key={b.txt + i}
            txt={b.txt}
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
  padding: 35px;
  span[data-role="txt"] {
    font-size: 48px;
  }
`;

const ButtonsGrid = styled("div")`
  display: flex;
  flex-direction: column;
  justify-content: space-around;
  padding-left: 25px;
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
