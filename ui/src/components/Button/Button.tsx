import { type ReactElement, type ReactNode } from "react";
import { ButtonVariantStyles, type ButtonVariant } from "./const";
import { useMemoValue } from "@utils/hooks/useMemoValue";

type Props = {
  txt: string;
  onClick?: () => void;
  startIcon?: ReactNode;
  variant?: ButtonVariant;
  type?: "submit" | "reset" | "button";
  disabled?: boolean;
  className?: string;
};

const BaseButton = ({
  txt,
  onClick,
  disabled,
  variant = "black-outlined",
  type = "button",
  startIcon,
  className,
}: Props): ReactElement => {
  const Button = useMemoValue((v) => ButtonVariantStyles[v], [variant]);
  return (
    <Button
      onClick={onClick}
      type={type}
      disabled={disabled}
      className={className}
    >
      {startIcon}
      <span data-role="txt">{txt}</span>
    </Button>
  );
};

export default BaseButton;
