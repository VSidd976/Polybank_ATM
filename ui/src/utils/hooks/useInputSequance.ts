import { useEffect, useRef, type RefObject } from "react";
import { useMemoValue } from "./useMemoValue";
import { microQueue } from "@utils/microQueue";

export type ControlledInput = {
  inputRef: (ref: HTMLInputElement) => void;
  idx: number;
  value: string;
};

function createInputs(
  refs: RefObject<HTMLInputElement[]>,
  values: string[],
): ControlledInput[] {
  return values.map((_, idx) => ({
    idx,
    inputRef: (el) => (refs.current[idx] = el),
    value: values[idx],
  }));
}

function selectInput(idx: number, refs: RefObject<HTMLInputElement[]>): void {
  const input = refs.current.at(idx);
  if (!input) return;
  microQueue(() => {
    input.focus();
    input.setSelectionRange(input.value.length, input.value.length);
  });
}

export const useInputSequance = (
  values: string[],
  selectedIdx: number,
): ControlledInput[] => {
  const refs = useRef<HTMLInputElement[]>([]);
  useEffect(() => selectInput(selectedIdx, refs), [selectedIdx, refs]);
  const inputs = useMemoValue(createInputs, [refs, values]);
  return inputs;
};
