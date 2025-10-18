import { styled } from "@mui/material";
import type { ControlledInput } from "@utils/hooks/useInputSequance";
import { useInputsStore } from "@utils/stores/inputStore";
import {
  useCallback,
  useMemo,
  type KeyboardEvent,
  type ReactElement,
} from "react";

const InputPart = ({ value, inputRef, idx }: ControlledInput): ReactElement => {
  const { onPrev, onNext, selectedIdx } = useInputsStore();
  const isSelected = useMemo(() => selectedIdx === idx, [selectedIdx, idx]);
  const onKeyDown = useCallback(
    (e: KeyboardEvent<HTMLInputElement>) => onInputChange(e, onPrev, onNext),
    [onNext, onPrev],
  );
  return (
    <BorderWrapper key={idx}>
      <Input
        ref={inputRef}
        value={value}
        name={`input-${idx}`}
        onKeyDown={onKeyDown}
        onChange={() => void 0}
        maxLength={1}
        disabled={!isSelected}
      />
    </BorderWrapper>
  );
};

function onInputChange(
  e: KeyboardEvent<HTMLInputElement>,
  onPrev: () => void,
  onNext: (val: string) => void,
) {
  e.preventDefault();
  if (e.key === "Backspace") {
    return onPrev();
  }
  if (/^\d$/.test(e.key)) {
    return onNext(e.key);
  }
}

export default InputPart;

const Input = styled("input")`
  display: block;
  width: 65px;
  height: 65px;
  font-size: 22px;
  border-radius: 20px;
  border: none;
  outline: none;
  vertical-align: middle;
  transition: all 0.3s ease;
  text-align: center;
  z-index: 1;
  background: ${({ theme }) => theme.palette.background.paper};
  opacity: 95%;
  &:disabled[value=""] {
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
