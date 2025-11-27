import { Modal as Modal_, styled } from "@mui/material";
import type { ComponentPropsWithoutRef } from "react";

export const BaseModal = ({
  children,
  ...props
}: ComponentPropsWithoutRef<typeof Modal>) => {
  return <Modal {...props}>{children}</Modal>;
};

const Modal = styled(Modal_)`
  display: flex;
  align-items: center;
  justify-content: center;
`;
