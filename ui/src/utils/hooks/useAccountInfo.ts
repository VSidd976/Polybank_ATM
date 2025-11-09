import AtmAPI, { type AccountInfo } from "@api/AtmAPI";
import { useCard } from "@utils/stores/cardStore";
import { useEffect, useState } from "react";
import { useMemoValue } from "./useMemoValue";

export const useAccountInfo = () => {
  const { card } = useCard();
  const [accountInfo, setInfo] = useState<AccountInfo>();
  const api = useMemoValue((c) => (c ? AtmAPI.of(c) : undefined), [card]);
  useEffect(() => {
    if (api) {
      api.getInfo().then((i) => setInfo(i));
    }
  }, [api]);
  return accountInfo;
};
