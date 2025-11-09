import { styled } from "@mui/material";
import { type ReactElement } from "react";

type Props = {
  onChange?: (v: string) => void;
  placeholder?: string;
  type?: string;
  name?: string;
  min?: string | number;
  max?: string | number;
  step?: number;
};

const Input = ({
  placeholder,
  type,
  name,
  min,
  max,
  step,
  onChange,
}: Props): ReactElement => {
  return (
    <BorderWrapper>
      <InputBase
        onChange={(e) => onChange?.(e.target.value)}
        type={type}
        name={name}
        step={step}
        min={min}
        max={max}
        placeholder={placeholder}
      />
    </BorderWrapper>
  );
};

export default Input;

const InputBase = styled("input")`
  display: block;
  font-size: 22px;
  border-radius: 20px;
  border: none;
  outline: none;
  padding: 10px 15px;
  vertical-align: middle;
  transition: all 0.3s ease;
  text-align: center;
  z-index: 1;
  background: ${({ theme }) => theme.palette.background.paper};
  opacity: 95%;
  &:read-only[value=""] {
    background: ${({ theme }) => theme.palette.background.paper};
    opacity: 85%;
  }
  color: ${({ theme }) => theme.palette.primary.contrastText};
  position: relative;
`;

const BorderWrapper = styled("div")(
  ({ theme }) => `
  position: relative;
  border-radius: 20px;
  padding: 3px;
  width: fit-content;
  height: fit-content;
  z-index: 1;
  overflow: hidden;
  display: inline-block;
  transition: transform 0.2s ease, filter 0.2s ease;

  &::before {
    content: "";
    position: absolute;
    inset: 0;
    border-radius: 20px;
    background: linear-gradient(270deg, ${theme.palette.secondary.main}, ${theme.palette.primary.light}, ${theme.palette.secondary.main});
    background-size: 600% 600%;
    animation: gradientMove 4s linear infinite;
    z-index: 0;

    -webkit-mask: linear-gradient(#fff 0 0) content-box, linear-gradient(#fff 0 0);
    -webkit-mask-composite: xor;
    mask-composite: exclude;
    mask: linear-gradient(#fff 0 0) content-box, linear-gradient(#fff 0 0);
  }

  &:hover {
    transform: scale(1.02);
  }

  &:active {
    transform: scale(0.98);
    filter: brightness(0.95);
  }

  @keyframes gradientMove {
    0% {
      background-position: 0% 50%;
    }
    50% {
      background-position: 100% 50%;
    }
    100% {
      background-position: 0% 50%;
    }
  }
`,
);
