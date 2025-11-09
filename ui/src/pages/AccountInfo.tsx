import { BackButton } from "@components/Button/BackButton";
import { styled } from "@mui/material";
import { useAccountInfo } from "@utils/hooks/useAccountInfo";
import type { ReactElement } from "react";

const AccountInfo = (): ReactElement => {
  const accountInfo = useAccountInfo();
  return (
    <Container>
      <BackButton />
      <Field>Balance: {accountInfo?.balance}</Field>
    </Container>
  );
};

export default AccountInfo;

const Container = styled("div")`
  width: 100%;
  display: flex;
  justify-content: center;
  align-items: center;
  position: relative;
  overflow: hidden;
`;

const Field = styled("p")`
  font-size: 22px;
  color: #bfbfbf;
  font-weight: 300;
`;
