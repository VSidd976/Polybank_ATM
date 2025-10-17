import { type ForwardedRef, forwardRef, type ReactElement } from "react";
import { ButtonVariantStyles, type ButtonVariant } from "./const";
import { useMemoValue } from "@utils/hooks/useMemoValue";

type Props = {
  txt: string;
  onClick?: () => void;
  variant?: ButtonVariant;
  className?: string;
};

const BaseButton = (
  { txt, onClick, variant = "black-outlined", className }: Props,
  ref: ForwardedRef<HTMLButtonElement>,
): ReactElement => {
  const Button = useMemoValue((v) => ButtonVariantStyles[v], [variant]);
  return (
    <Button onClick={onClick} className={className} ref={ref}>
      <span data-role="txt">{txt}</span>
    </Button>
  );
};

export default forwardRef(BaseButton);
