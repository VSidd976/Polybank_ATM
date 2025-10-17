import { useEffect, useRef, type RefObject } from "react";
import { useMemoValue } from "./useMemoValue";
import { useInputsStore } from "@utils/stores/inputStore";
import { microQueue } from "@utils/microQueue";

export type ControlledInput = {
  inputRef: (ref: HTMLInputElement) => void;
  isSelected: boolean;
  idx: number;
  value: string;
};

type InputsControls = {
  onNext: (val: string) => void;
  onPrev: () => void;
};

function createInputs(
  n: number,
  refs: RefObject<HTMLInputElement[]>,
  selectedIdx: number,
  values: string[],
): ControlledInput[] {
  return Array.from({ length: n }).map((_, idx) => ({
    idx,
    inputRef: (el) => (refs.current[idx] = el),
    value: values[idx],
    isSelected: selectedIdx === idx,
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
  amount: number,
): [ControlledInput[], InputsControls] => {
  const refs = useRef<HTMLInputElement[]>([]);
  const { selectedIdx, values, ...controls } = useInputsStore();
  useEffect(() => selectInput(selectedIdx, refs), [selectedIdx, refs]);
  const inputs = useMemoValue(createInputs, [
    amount,
    refs,
    selectedIdx,
    values,
  ]);

  return [inputs, controls] as const;
};
