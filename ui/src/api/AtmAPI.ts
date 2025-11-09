import type { Card } from "@components/BankCard/consts";
import axios from "axios";

export type AccountInfo = {
  balance: number;
};

const BASE_URL = "http://localhost:8000";

class AtmAPI {
  constructor(private readonly card: Card) {}

  static of(card: Card): AtmAPI {
    return new AtmAPI(card);
  }
  async insertCard(): Promise<void> {
    console.log("INSERTING");
    return await axios.post(`${BASE_URL}/card/accept`, {
      ownerName: this.card.ownerName,
      cardNumber: this.card.number,
      bankName: this.card.bank,
      cvv: this.card.cvv,
      expirationDate: this.card.expDate,
    });
  }

  async inputPIN(pin: string): Promise<boolean> {
    console.log("Sending a pin", pin);
    return await axios.post(`${BASE_URL}/card/accept/pin`, {
      ownerName: this.card.ownerName,
      cardNumber: this.card.number,
      bankName: this.card.bank,
      cvv: this.card.cvv,
      expirationDate: this.card.expDate,
      pin: pin,
    });
  }

  async cashOut(amount: number): Promise<boolean> {
    console.log({ amount, card: this.card });
    return await axios.post(`${BASE_URL}/account/take`, { cash: amount });
  }

  async putMoney(amount: number): Promise<boolean> {
    console.log({ amount, card: this.card });
    return await axios.post(`${BASE_URL}/account/put`, { cash: amount });
  }

  async transferMoney(amount: number, to: string): Promise<boolean> {
    console.log({ amount, to });
    return true;
  }

  async getInfo(): Promise<AccountInfo> {
    return {
      balance: 200,
    };
  }

  async endSession(): Promise<void> {
    return axios.put(`${BASE_URL}/card/return`);
  }
}

export default AtmAPI;
