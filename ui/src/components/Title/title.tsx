import { styled } from "@mui/material";
import type { PropsWithChildren, ReactElement } from "react";

type Props = { className?: string };

export const Title = ({
  children,
  className,
}: PropsWithChildren<Props>): ReactElement => {
  return <Title_ className={className}>{children}</Title_>;
};

const Title_ = styled("h2")`
  color: ${({ theme }) => theme.palette.info.contrastText};
`;
