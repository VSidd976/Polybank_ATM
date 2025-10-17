import { styled } from "@mui/material";
import type { ReactElement } from "react";
import Logo from "@assets/logo.svg";

const Header = (): ReactElement => {
  return (
    <Container>
      <img src={Logo} width={142} />
      <h1>ATM</h1>
    </Container>
  );
};

export default Header;

const Container = styled("div")`
  display: flex;
  z-index: 2;
  gap: 25px;
  background-color: ${({ theme }) => theme.palette.background.paper};
  padding: 20px 25px;
  & > h1 {
    color: ${({ theme }) => theme.palette.primary.contrastText};
    font-weight: 200;
  }
`;
