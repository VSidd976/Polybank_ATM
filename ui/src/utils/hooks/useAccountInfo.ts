import { useAtmApi, type AccountInfo } from "@api/AtmAPI";
import { useEffect, useState } from "react";

export const useAccountInfo = () => {
  const [accountInfo, setInfo] = useState<AccountInfo>();
  const api = useAtmApi({ onSuccess: (i) => setInfo(i) });
  useEffect(() => {
    if (api) {
      api.getInfo().then(setInfo);
    }
  }, [api]);
  return accountInfo;
};
