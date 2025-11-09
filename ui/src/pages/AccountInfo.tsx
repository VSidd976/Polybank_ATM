import { BackButton } from "@components/Button/BackButton";
import { styled } from "@mui/material";
import { useAccountInfo } from "@utils/hooks/useAccountInfo";
import { useCard } from "@utils/stores/cardStore";
import type { ReactElement } from "react";

const AccountInfo = (): ReactElement => {
  const accountInfo = useAccountInfo();
  const { card } = useCard();
  return (
    <Container>
      <BackButton />
      <Field>Name: {card?.ownerName ?? "Not mentioned"}</Field>
      <Field>Balance: {accountInfo?.balance}$(ukr hryvnya)</Field>
    </Container>
  );
};

export default AccountInfo;

const Container = styled("div")`
  width: 100%;
  display: flex;
  justify-content: center;
  align-items: center;
  flex-direction: column;
  gap: 12px;
  position: relative;
  overflow: hidden;
`;

const Field = styled("p")`
  font-size: 22px;
  color: #bfbfbf;
  font-weight: 300;
`;
