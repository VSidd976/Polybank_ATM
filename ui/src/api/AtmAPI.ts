import type { Card } from "@components/BankCard/consts";

class AtmAPI {
  private card: Card | undefined;
  static of(): AtmAPI {
    return new AtmAPI();
  }
  async insertCard(card: Card): Promise<boolean> {
    // impl
    console.log("Inserting a card", card);
    this.card = card;
    return true;
  }

  async inputPIN(pin: string): Promise<boolean> {
    console.log("Sending a pin", pin);
    return true;
  }

  async endSession(): Promise<void> {}
}

export const atmApi = AtmAPI.of();
