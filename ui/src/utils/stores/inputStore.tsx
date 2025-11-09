import {
  createContext,
  useContext,
  useRef,
  type PropsWithChildren,
} from "react";
import { createStore, useStore } from "zustand";

export type ControlledInput = {
  inputRef: (ref: HTMLInputElement) => void;
  isSelected: boolean;
  idx: number;
  value: string;
} & InputsControls;

type InputsControls = {
  onNext: (val: string) => void;
  onPrev: () => void;
};

interface InputsI {
  onNext(val: string): void;
  onPrev(): void;
  setValue(val: string): void;
  select(idx: number): void;
}

type InputsState = {
  values: string[];
  selectedIdx: number;
} & InputsI;

const createInputsStore = (amount: number) => {
  return createStore<InputsState>()((set, get) => ({
    values: Array.from({ length: amount }).map(() => ""),
    selectedIdx: 0,
    select: (idx: number) => set({ selectedIdx: idx }),
    setValue: (val: string) =>
      set((state) => {
        const { values, selectedIdx } = state;
        const newValues = [...values];
        newValues[selectedIdx] = val;
        return { values: newValues };
      }),
    onNext: (val: string) => {
      const { setValue, values, select, selectedIdx } = get();
      if (selectedIdx === amount - 1 && values[selectedIdx]) return;
      setValue(val);
      if (selectedIdx < amount - 1) select(selectedIdx + 1);
    },
    onPrev: () => {
      const { setValue, select, selectedIdx } = get();
      setValue("");
      if (selectedIdx > 0) select(selectedIdx - 1);
    },
  }));
};

const InputsContext = createContext<InputsState | null>(null);

export const InputStoreProvider = ({
  amount,
  children,
}: PropsWithChildren<{ amount: number }>) => {
  const store_ = useRef(createInputsStore(amount)).current;
  const store = useStore(store_);
  return (
    <InputsContext.Provider value={store}>{children}</InputsContext.Provider>
  );
};

export const useInputsStore = () => {
  const state = useContext(InputsContext);
  if (!state) throw new Error("No provider defined");
  return state;
};
