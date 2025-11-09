import { useCallback, useState } from "react";

type Controls = {
  toggle: () => void;
  on: () => void;
  off: () => void;
};

export const useBoolean = (initial: boolean = false): [boolean, Controls] => {
  const [state, setState] = useState(initial);
  const toggle = useCallback(() => setState((prev) => !prev), [setState]);
  const on = useCallback(() => setState(true), [setState]);
  const off = useCallback(() => setState(false), [setState]);

  return [state, { toggle, on, off } as const] as const;
};
