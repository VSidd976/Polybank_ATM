import BaseButton from "@components/Button/Button";
import { styled } from "@mui/material";
import { withProps } from "@utils/withProps";
import type { ReactElement } from "react";

const MainScreen = (): ReactElement => {
  return (
    <Container>
      <ButtonsGrid rows={2} cols={2}>
        <MenuButton txt="Button1" />
        <MenuButton txt="Button2" />
        <MenuButton txt="Button3" />
        <MenuButton txt="Button4" />
      </ButtonsGrid>
    </Container>
  );
};

export default MainScreen;

const MenuButton = styled(
  withProps(BaseButton, { variant: "rectangular" } as const),
)`
  padding: 25px;
`;

const ButtonsGrid = styled("div")<{ rows: number; cols: number }>`
  display: grid;
  grid-template-columns: repeat(${({ cols }) => cols}, 1fr);
  grid-template-rows: repeat(${({ rows }) => rows}, 1fr);
  gap: 12px;
`;

const Container = styled("div")`
  width: 100%;
  display: flex;
  justify-content: center;
  align-items: center;
  align-self: center;
`;
