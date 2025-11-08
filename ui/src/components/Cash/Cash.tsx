import { useCallback, type ReactElement } from "react";
import { CASH_NOMINALS, type Nominal } from "./const";
import { styled } from "@mui/material";
import { useMemoValue } from "@utils/hooks/useMemoValue";

type Props = {
  nominal: Nominal;
  onClick?: (n: Nominal) => void;
  className?: string;
};

const Cash = ({ nominal, onClick, className }: Props): ReactElement => {
  const src = useMemoValue((_nominal) => CASH_NOMINALS[_nominal], [nominal]);
  const click = useCallback(() => onClick?.(nominal), [nominal]);
  return (
    <Container className={className} onClick={click}>
      <img src={src} alt={`${nominal}`} width={300} height={160} />
    </Container>
  );
};

export default Cash;

const Container = styled("div")``;
