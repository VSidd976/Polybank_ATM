import { type ReactElement } from "react";
import { ButtonVariantStyles, type ButtonVariant } from "./const";
import { useMemoValue } from "@utils/hooks/useMemoValue";

type Props = {
  txt: string;
  onClick?: () => void;
  variant?: ButtonVariant;
  type?: "submit" | "reset" | "button";
  className?: string;
};

const BaseButton = ({
  txt,
  onClick,
  variant = "black-outlined",
  type = "button",
  className,
}: Props): ReactElement => {
  const Button = useMemoValue((v) => ButtonVariantStyles[v], [variant]);
  return (
    <Button onClick={onClick} type={type} className={className}>
      <span data-role="txt">{txt}</span>
    </Button>
  );
};

export default BaseButton;
