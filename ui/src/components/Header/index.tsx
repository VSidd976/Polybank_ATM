import { styled } from "@mui/material";
import type { ReactElement } from "react";
import Logo from "@assets/logo.svg";
import ExitToAppIcon from "@mui/icons-material/ExitToApp";
import BaseButton from "@components/Button/Button";
import { withProps } from "@utils/withProps";
import { useLocation, useNavigate } from "react-router-dom";

const useLogout = (): {
  isLogoutVisible: boolean;
  onLogout: () => void | Promise<void>;
} => {
  const location = useLocation();
  const navigate = useNavigate();
  const isLogoutVisible = location.pathname === "/main";
  const onLogout = () => navigate("/?logout=true");
  return { isLogoutVisible, onLogout };
};

const Header = (): ReactElement => {
  const { isLogoutVisible, onLogout } = useLogout();
  return (
    <Container>
      <img src={Logo} width={142} />
      <h1>ATM</h1>
      {isLogoutVisible && <LogoutButton onClick={onLogout} />}
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

const LogoutButton = styled(
  withProps(BaseButton, {
    txt: "Logout",
    startIcon: <ExitToAppIcon />,
  } as const),
)`
  display: flex;
  align-items: center;
  margin-left: auto;
`;
